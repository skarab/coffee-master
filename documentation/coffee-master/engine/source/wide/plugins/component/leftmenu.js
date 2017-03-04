function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6424\" class=\"headerLeftMenuInActive\"><a id=\"aID6424\" href=\"#\" OnMouseOver=\"link('_dir','component0',this)\" class=\"leftMenuLinkHeadInActive\">component</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID952\" class=\"leftMenuInActive\"><a id=\"aID952\" href=\"#\" OnMouseOver=\"link('_class','Component12811',this)\" class=\"leftMenuLinkInActive\">Component</a></div>\n");
document.write("<div id=\"divID955\" class=\"leftMenuInActive\"><a id=\"aID955\" href=\"#\" OnMouseOver=\"link('_class','ComponentLibrary12811',this)\" class=\"leftMenuLinkInActive\">ComponentLibrary</a></div>\n");
document.write("<div id=\"divID953\" class=\"leftMenuInActive\"><a id=\"aID953\" href=\"#\" OnMouseOver=\"link('_class','ComponentObject12811',this)\" class=\"leftMenuLinkInActive\">ComponentObject</a></div>\n");
document.write("<div id=\"divID954\" class=\"leftMenuInActive\"><a id=\"aID954\" href=\"#\" OnMouseOver=\"link('_class','ComponentWrapper12811',this)\" class=\"leftMenuLinkInActive\">ComponentWrapper</a></div>\n");
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
