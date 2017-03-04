function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6306\" class=\"headerLeftMenuInActive\"><a id=\"aID6306\" href=\"#\" OnMouseOver=\"link('_dir','meta0',this)\" class=\"leftMenuLinkHeadInActive\">meta</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6302\" class=\"leftMenuInActive\"><a id=\"aID6302\" href=\"#\" OnMouseOver=\"link('_dir','array/array0',this)\" class=\"leftMenuLinkInActive\">array</a></div>\n");
document.write("<div id=\"divID6303\" class=\"leftMenuInActive\"><a id=\"aID6303\" href=\"#\" OnMouseOver=\"link('_dir','helpers/helpers0',this)\" class=\"leftMenuLinkInActive\">helpers</a></div>\n");
document.write("<div id=\"divID6304\" class=\"leftMenuInActive\"><a id=\"aID6304\" href=\"#\" OnMouseOver=\"link('_dir','info/info0',this)\" class=\"leftMenuLinkInActive\">info</a></div>\n");
document.write("<div id=\"divID6305\" class=\"leftMenuInActive\"><a id=\"aID6305\" href=\"#\" OnMouseOver=\"link('_dir','macros/macros0',this)\" class=\"leftMenuLinkInActive\">macros</a></div>\n");
document.write("<div id=\"divID6307\" class=\"leftMenuInActive\"><a id=\"aID6307\" href=\"#\" OnMouseOver=\"link('_dir','param/param0',this)\" class=\"leftMenuLinkInActive\">param</a></div>\n");
document.write("<div id=\"divID6309\" class=\"leftMenuInActive\"><a id=\"aID6309\" href=\"#\" OnMouseOver=\"link('_dir','serializer/serializer0',this)\" class=\"leftMenuLinkInActive\">serializer</a></div>\n");
document.write("<div id=\"divID6313\" class=\"leftMenuInActive\"><a id=\"aID6313\" href=\"#\" OnMouseOver=\"link('_dir','type/type0',this)\" class=\"leftMenuLinkInActive\">type</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID772\" class=\"leftMenuInActive\"><a id=\"aID772\" href=\"#\" OnMouseOver=\"link('_class','Object53261',this)\" class=\"leftMenuLinkInActive\">Object</a></div>\n");
document.write("<div id=\"divID773\" class=\"leftMenuInActive\"><a id=\"aID773\" href=\"#\" OnMouseOver=\"link('_class','Types53261',this)\" class=\"leftMenuLinkInActive\">Types</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1240\" class=\"leftMenuInActive\"><a id=\"aID1240\" href=\"#\" OnMouseOver=\"link('_member','MODE1371500270',this)\" class=\"leftMenuLinkInActive\">MODE</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6214\" class=\"leftMenuInActive\"><a id=\"aID6214\" href=\"#\" OnMouseOver=\"link('_member','MODE240823',this)\" class=\"leftMenuLinkInActive\">MODE</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
