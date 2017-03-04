function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6313\" class=\"headerLeftMenuInActive\"><a id=\"aID6313\" href=\"#\" OnMouseOver=\"link('_dir','type0',this)\" class=\"leftMenuLinkHeadInActive\">type</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6311\" class=\"leftMenuInActive\"><a id=\"aID6311\" href=\"#\" OnMouseOver=\"link('_dir','class/class0',this)\" class=\"leftMenuLinkInActive\">class</a></div>\n");
document.write("<div id=\"divID6312\" class=\"leftMenuInActive\"><a id=\"aID6312\" href=\"#\" OnMouseOver=\"link('_dir','enum/enum0',this)\" class=\"leftMenuLinkInActive\">enum</a></div>\n");
document.write("<div id=\"divID6314\" class=\"leftMenuInActive\"><a id=\"aID6314\" href=\"#\" OnMouseOver=\"link('_dir','scalar/scalar0',this)\" class=\"leftMenuLinkInActive\">scalar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID795\" class=\"leftMenuInActive\"><a id=\"aID795\" href=\"#\" OnMouseOver=\"link('_class','Type53261',this)\" class=\"leftMenuLinkInActive\">Type</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Structs</div>\n");
document.write("<div id=\"divID796\" class=\"leftMenuInActive\"><a id=\"aID796\" href=\"#\" OnMouseOver=\"link('_class','TYPE20541',this)\" class=\"leftMenuLinkInActive\">TYPE<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6216\" class=\"leftMenuInActive\"><a id=\"aID6216\" href=\"#\" OnMouseOver=\"link('_member','TYPE_INFO240823',this)\" class=\"leftMenuLinkInActive\">TYPE_INFO</a></div>\n");
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
