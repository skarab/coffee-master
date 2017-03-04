function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6394\" class=\"headerLeftMenuInActive\"><a id=\"aID6394\" href=\"#\" OnMouseOver=\"link('_dir','physics0',this)\" class=\"leftMenuLinkHeadInActive\">physics</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6393\" class=\"leftMenuInActive\"><a id=\"aID6393\" href=\"#\" OnMouseOver=\"link('_dir','material/material0',this)\" class=\"leftMenuLinkInActive\">material</a></div>\n");
document.write("<div id=\"divID6402\" class=\"leftMenuInActive\"><a id=\"aID6402\" href=\"#\" OnMouseOver=\"link('_dir','rigid_body/rigid_body0',this)\" class=\"leftMenuLinkInActive\">rigid_body</a></div>\n");
document.write("<div id=\"divID6404\" class=\"leftMenuInActive\"><a id=\"aID6404\" href=\"#\" OnMouseOver=\"link('_dir','scene/scene0',this)\" class=\"leftMenuLinkInActive\">scene</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID912\" class=\"leftMenuInActive\"><a id=\"aID912\" href=\"#\" OnMouseOver=\"link('_class','Component14855',this)\" class=\"leftMenuLinkInActive\">Component</a></div>\n");
document.write("<div id=\"divID913\" class=\"leftMenuInActive\"><a id=\"aID913\" href=\"#\" OnMouseOver=\"link('_class','World14855',this)\" class=\"leftMenuLinkInActive\">World</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Structs</div>\n");
document.write("<div id=\"divID911\" class=\"leftMenuInActive\"><a id=\"aID911\" href=\"#\" OnMouseOver=\"link('_class','Collision14855',this)\" class=\"leftMenuLinkInActive\">Collision</a></div>\n");
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
