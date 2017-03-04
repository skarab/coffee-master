function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6307\" class=\"headerLeftMenuInActive\"><a id=\"aID6307\" href=\"#\" OnMouseOver=\"link('_dir','param0',this)\" class=\"leftMenuLinkHeadInActive\">param</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6308\" class=\"leftMenuInActive\"><a id=\"aID6308\" href=\"#\" OnMouseOver=\"link('_dir','scalar/scalar0',this)\" class=\"leftMenuLinkInActive\">scalar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID775\" class=\"leftMenuInActive\"><a id=\"aID775\" href=\"#\" OnMouseOver=\"link('_class','Param53261',this)\" class=\"leftMenuLinkInActive\">Param</a></div>\n");
document.write("<div id=\"divID776\" class=\"leftMenuInActive\"><a id=\"aID776\" href=\"#\" OnMouseOver=\"link('_class','ParamArray53261',this)\" class=\"leftMenuLinkInActive\">ParamArray</a></div>\n");
document.write("<div id=\"divID777\" class=\"leftMenuInActive\"><a id=\"aID777\" href=\"#\" OnMouseOver=\"link('_class','ParamArrayCombo53261',this)\" class=\"leftMenuLinkInActive\">ParamArrayCombo</a></div>\n");
document.write("<div id=\"divID778\" class=\"leftMenuInActive\"><a id=\"aID778\" href=\"#\" OnMouseOver=\"link('_class','ParamEnumMulti53261',this)\" class=\"leftMenuLinkInActive\">ParamEnumMulti</a></div>\n");
document.write("<div id=\"divID779\" class=\"leftMenuInActive\"><a id=\"aID779\" href=\"#\" OnMouseOver=\"link('_class','ParamProperty53261',this)\" class=\"leftMenuLinkInActive\">ParamProperty</a></div>\n");
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
