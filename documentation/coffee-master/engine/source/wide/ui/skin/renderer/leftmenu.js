function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6439\" class=\"headerLeftMenuInActive\"><a id=\"aID6439\" href=\"#\" OnMouseOver=\"link('_dir','renderer0',this)\" class=\"leftMenuLinkHeadInActive\">renderer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID993\" class=\"leftMenuInActive\"><a id=\"aID993\" href=\"#\" OnMouseOver=\"link('_class','SkinRenderer49249',this)\" class=\"leftMenuLinkInActive\">SkinRenderer</a></div>\n");
document.write("<div id=\"divID994\" class=\"leftMenuInActive\"><a id=\"aID994\" href=\"#\" OnMouseOver=\"link('_class','SkinRendererBasic49249',this)\" class=\"leftMenuLinkInActive\">SkinRendererBasic</a></div>\n");
document.write("<div id=\"divID995\" class=\"leftMenuInActive\"><a id=\"aID995\" href=\"#\" OnMouseOver=\"link('_class','SkinRendererRounded49249',this)\" class=\"leftMenuLinkInActive\">SkinRendererRounded</a></div>\n");
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
